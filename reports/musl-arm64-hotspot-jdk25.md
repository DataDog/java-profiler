---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-09 10:23:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 12 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 266 |
| Sample Rate | 4.43/sec |
| Health Score | 277% |
| Threads | 11 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1791555457 36
1791555462 36
1791555467 36
1791555472 36
1791555477 36
1791555482 36
1791555487 36
1791555492 36
1791555497 36
1791555502 36
1791555507 36
1791555512 36
1791555517 36
1791555522 36
1791555527 36
1791555532 36
1791555538 31
1791555543 31
1791555548 31
1791555553 31
```
</details>

---

