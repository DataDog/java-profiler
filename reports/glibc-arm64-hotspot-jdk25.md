---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-14 01:03:57 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 14 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 17-18 cores)</summary>

```
1791953980 18
1791953985 18
1791953990 18
1791953995 18
1791954000 17
1791954005 17
1791954010 17
1791954015 17
1791954020 18
1791954025 18
1791954030 18
1791954035 18
1791954040 18
1791954045 18
1791954050 17
1791954055 17
1791954060 17
1791954065 17
1791954070 17
1791954075 17
```
</details>

---

