---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 05:55:45 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1791280164 51
1791280169 51
1791280174 51
1791280179 51
1791280184 51
1791280189 51
1791280194 51
1791280199 51
1791280204 51
1791280209 51
1791280214 51
1791280219 51
1791280224 51
1791280229 51
1791280234 51
1791280239 51
1791280244 51
1791280249 51
1791280254 51
1791280259 51
```
</details>

---

