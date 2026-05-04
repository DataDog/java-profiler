---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-03 21:22:25 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 11 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (3 unique values: 41-47 cores)</summary>

```
1777857116 41
1777857121 41
1777857126 43
1777857131 43
1777857136 43
1777857141 43
1777857146 47
1777857151 47
1777857156 47
1777857161 47
1777857166 47
1777857171 47
1777857176 47
1777857181 47
1777857186 47
1777857191 47
1777857196 47
1777857201 47
1777857206 47
1777857211 47
```
</details>

---

