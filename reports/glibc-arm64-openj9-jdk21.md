---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 15:18:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 10 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 31-51 cores)</summary>

```
1792610119 46
1792610124 46
1792610129 51
1792610134 51
1792610139 51
1792610144 51
1792610149 51
1792610154 51
1792610159 51
1792610164 51
1792610169 31
1792610174 31
1792610179 31
1792610184 31
1792610189 31
1792610194 31
1792610199 31
1792610204 31
1792610209 31
1792610214 31
```
</details>

---

