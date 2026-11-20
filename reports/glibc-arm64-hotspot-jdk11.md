---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 11:32:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 320 |
| Sample Rate | 5.33/sec |
| Health Score | 333% |
| Threads | 10 |
| Allocations | 201 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 960 |
| Sample Rate | 16.00/sec |
| Health Score | 1000% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795192122 50
1795192127 50
1795192132 50
1795192137 50
1795192142 50
1795192147 50
1795192152 50
1795192157 50
1795192162 50
1795192167 50
1795192172 50
1795192177 50
1795192182 50
1795192187 50
1795192192 50
1795192197 50
1795192202 50
1795192207 50
1795192212 50
1795192218 50
```
</details>

---

