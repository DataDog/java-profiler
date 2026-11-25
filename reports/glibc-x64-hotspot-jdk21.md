---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 12:29:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 9 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 9 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 85-93 cores)</summary>

```
1795627432 93
1795627437 93
1795627442 93
1795627447 93
1795627452 93
1795627457 93
1795627462 93
1795627467 93
1795627472 93
1795627477 93
1795627482 93
1795627487 93
1795627492 85
1795627497 85
1795627502 85
1795627507 85
1795627512 85
1795627517 85
1795627522 85
1795627527 85
```
</details>

---

