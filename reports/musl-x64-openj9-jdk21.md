---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 08:54:46 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 433 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1793800140 56
1793800145 56
1793800150 56
1793800155 56
1793800161 56
1793800166 56
1793800171 56
1793800176 51
1793800181 51
1793800186 51
1793800191 51
1793800196 51
1793800201 51
1793800206 51
1793800211 51
1793800216 56
1793800221 56
1793800226 56
1793800231 56
1793800236 56
```
</details>

---

