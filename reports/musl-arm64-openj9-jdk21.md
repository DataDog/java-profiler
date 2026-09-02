---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-02 09:19:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1788354649 64
1788354654 64
1788354659 64
1788354664 64
1788354669 64
1788354674 64
1788354679 64
1788354684 64
1788354689 64
1788354694 62
1788354699 62
1788354704 62
1788354709 62
1788354714 62
1788354719 62
1788354724 62
1788354729 62
1788354734 62
1788354739 62
1788354744 62
```
</details>

---

