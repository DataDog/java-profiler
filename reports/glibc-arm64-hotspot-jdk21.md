---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-19 06:50:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (4 unique values: 34-40 cores)</summary>

```
1792406808 40
1792406813 40
1792406818 35
1792406823 35
1792406828 35
1792406833 35
1792406838 34
1792406843 34
1792406848 34
1792406853 34
1792406858 34
1792406863 34
1792406868 34
1792406873 34
1792406878 34
1792406883 39
1792406888 39
1792406893 39
1792406898 39
1792406903 39
```
</details>

---

