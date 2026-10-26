---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 12:32:05 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 7 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 12 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1793032002 44
1793032007 44
1793032012 44
1793032017 44
1793032022 44
1793032028 44
1793032033 44
1793032038 44
1793032043 44
1793032048 48
1793032053 48
1793032058 48
1793032063 48
1793032068 48
1793032073 48
1793032078 48
1793032083 48
1793032088 48
1793032093 48
1793032098 48
```
</details>

---

