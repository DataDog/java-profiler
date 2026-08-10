---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-10 01:00:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 14 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1786337836 32
1786337841 34
1786337846 34
1786337851 34
1786337856 34
1786337861 34
1786337866 34
1786337871 34
1786337876 34
1786337881 34
1786337886 34
1786337891 34
1786337896 34
1786337901 34
1786337906 34
1786337911 34
1786337916 34
1786337921 34
1786337926 34
1786337931 34
```
</details>

---

