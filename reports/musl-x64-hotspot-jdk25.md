---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 08:26:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 72-88 cores)</summary>

```
1795785636 86
1795785641 86
1795785646 86
1795785651 86
1795785656 86
1795785661 86
1795785666 86
1795785671 86
1795785676 86
1795785681 86
1795785686 86
1795785691 86
1795785696 86
1795785701 86
1795785706 86
1795785711 88
1795785716 88
1795785721 88
1795785726 88
1795785731 88
```
</details>

---

