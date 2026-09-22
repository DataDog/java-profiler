---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 11:47:43 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 83 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790091752 50
1790091757 50
1790091762 50
1790091767 50
1790091772 50
1790091777 50
1790091782 50
1790091787 50
1790091792 50
1790091797 50
1790091802 50
1790091807 50
1790091812 50
1790091817 50
1790091822 50
1790091827 50
1790091832 50
1790091837 50
1790091842 50
1790091847 50
```
</details>

---

