---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 11:36:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 11 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 915 |
| Sample Rate | 15.25/sec |
| Health Score | 953% |
| Threads | 12 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 49-53 cores)</summary>

```
1770136117 53
1770136122 53
1770136127 53
1770136132 53
1770136137 53
1770136142 53
1770136147 53
1770136152 53
1770136157 53
1770136162 53
1770136167 51
1770136172 51
1770136177 51
1770136182 49
1770136187 49
1770136192 53
1770136197 53
1770136202 53
1770136207 53
1770136212 53
```
</details>

---

