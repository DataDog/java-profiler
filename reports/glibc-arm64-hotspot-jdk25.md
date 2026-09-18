---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:07:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 35 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 11 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (7 unique values: 36-47 cores)</summary>

```
1789743597 38
1789743602 38
1789743607 38
1789743612 38
1789743617 37
1789743622 37
1789743627 37
1789743632 37
1789743637 36
1789743642 36
1789743647 41
1789743652 41
1789743657 41
1789743662 41
1789743667 41
1789743672 46
1789743677 46
1789743682 47
1789743687 47
1789743692 43
```
</details>

---

