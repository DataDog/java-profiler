---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-23 06:57:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 165 |
| Sample Rate | 2.75/sec |
| Health Score | 172% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 69-77 cores)</summary>

```
1795434769 69
1795434774 69
1795434779 71
1795434784 71
1795434789 71
1795434794 71
1795434799 76
1795434804 76
1795434809 76
1795434814 76
1795434819 76
1795434824 76
1795434829 76
1795434834 76
1795434839 76
1795434844 75
1795434849 75
1795434854 75
1795434859 75
1795434864 75
```
</details>

---

