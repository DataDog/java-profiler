---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:08:25 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789995901 48
1789995906 48
1789995911 48
1789995916 48
1789995921 48
1789995926 48
1789995931 48
1789995936 48
1789995941 48
1789995946 48
1789995951 48
1789995956 48
1789995961 48
1789995966 48
1789995971 48
1789995976 48
1789995981 48
1789995986 48
1789995991 48
1789995997 48
```
</details>

---

