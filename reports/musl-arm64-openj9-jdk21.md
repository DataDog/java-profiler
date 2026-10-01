---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-01 09:06:25 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (6 unique values: 32-48 cores)</summary>

```
1790859724 37
1790859729 37
1790859734 37
1790859739 37
1790859744 37
1790859749 37
1790859755 37
1790859760 37
1790859765 32
1790859770 32
1790859775 32
1790859780 32
1790859785 41
1790859790 41
1790859795 41
1790859800 41
1790859805 46
1790859810 46
1790859815 46
1790859820 48
```
</details>

---

