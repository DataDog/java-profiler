---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-01-27 11:39:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 201 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 25-32 cores)</summary>

```
1769531591 30
1769531596 30
1769531601 30
1769531606 30
1769531611 30
1769531616 30
1769531621 30
1769531626 30
1769531631 30
1769531636 30
1769531641 30
1769531646 30
1769531651 30
1769531656 30
1769531661 30
1769531666 30
1769531671 30
1769531676 30
1769531681 32
1769531686 32
```
</details>

---

