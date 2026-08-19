---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-19 01:04:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 11 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1787115672 24
1787115677 24
1787115682 34
1787115687 34
1787115692 34
1787115697 34
1787115702 34
1787115707 34
1787115712 34
1787115717 34
1787115722 34
1787115727 34
1787115732 34
1787115737 34
1787115742 34
1787115747 29
1787115752 29
1787115757 29
1787115762 29
1787115768 29
```
</details>

---

