---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:23:33 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 12 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1795195212 59
1795195217 59
1795195222 59
1795195227 64
1795195233 64
1795195238 59
1795195243 59
1795195248 59
1795195253 59
1795195258 59
1795195263 59
1795195268 59
1795195273 59
1795195278 59
1795195283 59
1795195288 59
1795195293 59
1795195298 59
1795195303 59
1795195308 44
```
</details>

---

