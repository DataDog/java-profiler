---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-28 00:48:43 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 14 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790570657 43
1790570662 43
1790570667 43
1790570672 43
1790570677 43
1790570682 43
1790570687 43
1790570692 43
1790570697 43
1790570702 43
1790570707 48
1790570712 48
1790570717 48
1790570722 48
1790570727 48
1790570732 48
1790570737 48
1790570742 48
1790570747 48
1790570752 48
```
</details>

---

