---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 20:59:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1793148861 55
1793148866 55
1793148871 55
1793148876 57
1793148881 57
1793148886 57
1793148891 57
1793148896 57
1793148901 57
1793148906 57
1793148911 57
1793148916 55
1793148921 55
1793148926 55
1793148931 55
1793148936 55
1793148941 55
1793148946 55
1793148951 57
1793148956 57
```
</details>

---

