---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 16:51:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 76-91 cores)</summary>

```
1793742154 81
1793742159 81
1793742164 81
1793742169 81
1793742174 81
1793742179 81
1793742184 81
1793742189 81
1793742194 81
1793742199 81
1793742204 81
1793742209 81
1793742214 89
1793742219 89
1793742224 91
1793742229 91
1793742234 91
1793742239 76
1793742244 76
1793742249 76
```
</details>

---

