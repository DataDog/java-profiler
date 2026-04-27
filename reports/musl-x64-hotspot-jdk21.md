---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-27 16:34:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 79-88 cores)</summary>

```
1777321753 83
1777321758 83
1777321763 85
1777321768 85
1777321773 85
1777321778 85
1777321783 85
1777321788 85
1777321793 85
1777321798 85
1777321803 85
1777321808 88
1777321813 88
1777321818 88
1777321823 88
1777321828 88
1777321833 88
1777321838 88
1777321843 88
1777321848 88
```
</details>

---

