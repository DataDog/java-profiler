---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 17:39:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (3 unique values: 87-91 cores)</summary>

```
1792532150 87
1792532155 89
1792532160 89
1792532165 89
1792532170 89
1792532175 89
1792532180 87
1792532185 87
1792532190 87
1792532195 87
1792532200 87
1792532205 87
1792532210 87
1792532215 89
1792532220 89
1792532225 89
1792532230 89
1792532235 89
1792532240 89
1792532245 89
```
</details>

---

