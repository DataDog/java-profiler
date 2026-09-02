---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-02 09:19:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1788354659 64
1788354664 64
1788354669 64
1788354674 64
1788354679 64
1788354684 64
1788354689 64
1788354694 64
1788354699 64
1788354704 64
1788354709 64
1788354714 64
1788354719 64
1788354724 64
1788354729 64
1788354734 64
1788354739 64
1788354744 64
1788354749 64
1788354754 64
```
</details>

---

