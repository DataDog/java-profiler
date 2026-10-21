---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 17:25:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 41 |
| Sample Rate | 0.68/sec |
| Health Score | 42% |
| Threads | 9 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 13-48 cores)</summary>

```
1792617691 48
1792617696 48
1792617701 48
1792617706 48
1792617711 48
1792617716 13
1792617721 13
1792617726 13
1792617731 13
1792617736 13
1792617742 13
1792617747 13
1792617752 13
1792617757 13
1792617762 13
1792617767 13
1792617772 13
1792617777 13
1792617782 13
1792617787 13
```
</details>

---

