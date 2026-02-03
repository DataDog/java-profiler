---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 11:36:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 33-38 cores)</summary>

```
1770136137 38
1770136142 38
1770136147 38
1770136152 38
1770136157 38
1770136162 38
1770136167 37
1770136172 37
1770136177 33
1770136182 33
1770136187 33
1770136192 33
1770136197 38
1770136202 38
1770136207 38
1770136212 38
1770136217 38
1770136222 38
1770136227 38
1770136232 38
```
</details>

---

