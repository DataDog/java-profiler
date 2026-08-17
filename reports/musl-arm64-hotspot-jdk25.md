---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-17 09:54:52 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 10 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1786974667 46
1786974672 46
1786974677 46
1786974682 46
1786974687 46
1786974692 46
1786974697 46
1786974702 46
1786974707 46
1786974712 46
1786974717 46
1786974722 46
1786974727 46
1786974732 48
1786974737 48
1786974742 48
1786974747 48
1786974752 48
1786974757 48
1786974762 48
```
</details>

---

