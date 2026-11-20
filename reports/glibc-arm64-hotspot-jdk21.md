---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:23:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795195208 50
1795195213 50
1795195218 50
1795195223 50
1795195228 50
1795195233 50
1795195238 50
1795195243 50
1795195248 50
1795195253 50
1795195258 50
1795195263 50
1795195268 50
1795195273 50
1795195278 50
1795195283 50
1795195288 50
1795195293 50
1795195298 50
1795195303 50
```
</details>

---

