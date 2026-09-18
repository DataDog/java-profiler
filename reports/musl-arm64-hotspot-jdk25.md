---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 03:39:52 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 267 |
| Sample Rate | 4.45/sec |
| Health Score | 278% |
| Threads | 10 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 11 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (3 unique values: 44-56 cores)</summary>

```
1789716556 44
1789716561 44
1789716566 44
1789716571 44
1789716576 44
1789716581 44
1789716586 44
1789716591 44
1789716596 44
1789716601 52
1789716606 52
1789716611 52
1789716616 52
1789716621 44
1789716626 44
1789716631 44
1789716636 44
1789716641 44
1789716646 44
1789716651 44
```
</details>

---

