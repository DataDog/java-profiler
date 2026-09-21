---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 07:21:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 21-47 cores)</summary>

```
1789989421 21
1789989426 21
1789989431 21
1789989436 45
1789989441 45
1789989446 25
1789989451 25
1789989456 25
1789989461 25
1789989466 25
1789989472 25
1789989477 47
1789989482 47
1789989487 47
1789989492 47
1789989497 47
1789989502 47
1789989507 21
1789989512 21
1789989517 21
```
</details>

---

