---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-01 16:11:19 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 11 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 292 |
| Sample Rate | 4.87/sec |
| Health Score | 304% |
| Threads | 14 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1777665806 64
1777665811 64
1777665816 64
1777665821 64
1777665826 64
1777665831 64
1777665836 64
1777665841 60
1777665846 60
1777665851 60
1777665856 60
1777665861 60
1777665866 60
1777665871 60
1777665876 60
1777665881 60
1777665886 60
1777665891 60
1777665896 60
1777665901 60
```
</details>

---

