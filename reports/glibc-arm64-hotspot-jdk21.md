---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-19 09:55:41 EDT

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 13 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 33-34 cores)</summary>

```
1787147505 33
1787147510 33
1787147515 33
1787147520 34
1787147525 34
1787147530 34
1787147535 34
1787147540 34
1787147545 34
1787147550 34
1787147555 34
1787147560 34
1787147565 34
1787147570 34
1787147575 34
1787147580 34
1787147585 34
1787147590 34
1787147595 34
1787147600 34
```
</details>

---

