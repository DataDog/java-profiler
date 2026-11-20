---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 05:01:33 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1795168571 34
1795168576 34
1795168581 34
1795168586 34
1795168591 34
1795168596 34
1795168601 34
1795168606 34
1795168611 34
1795168616 34
1795168621 34
1795168626 34
1795168631 34
1795168636 34
1795168641 32
1795168646 32
1795168651 32
1795168656 32
1795168661 32
1795168666 32
```
</details>

---

