---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-10 07:11:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770725159 30
1770725164 32
1770725169 32
1770725174 32
1770725179 32
1770725184 32
1770725189 32
1770725194 32
1770725199 32
1770725204 32
1770725209 32
1770725214 32
1770725219 32
1770725224 32
1770725229 32
1770725234 32
1770725239 32
1770725244 32
1770725249 32
1770725254 32
```
</details>

---

