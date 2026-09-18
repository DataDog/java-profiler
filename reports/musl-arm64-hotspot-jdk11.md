---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:50:57 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1789731836 45
1789731841 45
1789731846 45
1789731851 45
1789731856 45
1789731861 45
1789731866 45
1789731871 48
1789731876 48
1789731881 48
1789731886 48
1789731891 48
1789731896 48
1789731901 48
1789731906 48
1789731911 48
1789731916 48
1789731921 48
1789731926 48
1789731931 48
```
</details>

---

