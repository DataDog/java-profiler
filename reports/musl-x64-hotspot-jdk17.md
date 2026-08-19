---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-19 09:55:43 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1787147499 92
1787147504 92
1787147510 92
1787147515 92
1787147520 92
1787147525 92
1787147530 92
1787147535 96
1787147540 96
1787147545 96
1787147550 96
1787147555 96
1787147560 96
1787147565 96
1787147570 96
1787147575 96
1787147580 96
1787147585 96
1787147590 96
1787147595 96
```
</details>

---

