---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-02 09:19:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (5 unique values: 37-59 cores)</summary>

```
1788354698 39
1788354703 37
1788354708 37
1788354714 37
1788354719 37
1788354724 37
1788354729 57
1788354734 57
1788354739 57
1788354744 57
1788354749 57
1788354754 57
1788354759 56
1788354764 56
1788354769 56
1788354774 56
1788354779 59
1788354784 59
1788354789 59
1788354794 59
```
</details>

---

