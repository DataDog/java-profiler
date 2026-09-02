---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-02 09:19:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 9 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 17-64 cores)</summary>

```
1788354654 64
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
1788354734 17
1788354739 17
1788354744 17
1788354749 17
```
</details>

---

