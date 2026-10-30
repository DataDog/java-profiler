---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 06:28:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 36-52 cores)</summary>

```
1793355811 41
1793355816 41
1793355821 41
1793355826 36
1793355831 36
1793355836 36
1793355841 36
1793355846 36
1793355851 36
1793355856 36
1793355861 36
1793355866 36
1793355871 36
1793355876 36
1793355881 36
1793355886 41
1793355891 41
1793355896 52
1793355901 52
1793355906 52
```
</details>

---

