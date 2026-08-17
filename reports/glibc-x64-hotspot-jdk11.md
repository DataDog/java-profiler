---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:54:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 7 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1786974682 30
1786974687 30
1786974692 30
1786974697 30
1786974702 30
1786974707 30
1786974712 32
1786974717 32
1786974722 32
1786974727 32
1786974732 32
1786974737 32
1786974742 32
1786974747 32
1786974752 32
1786974757 32
1786974762 32
1786974767 32
1786974772 32
1786974777 32
```
</details>

---

