---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 00:06:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 72-81 cores)</summary>

```
1794978137 72
1794978142 72
1794978147 81
1794978152 81
1794978157 81
1794978162 81
1794978167 81
1794978172 81
1794978177 81
1794978182 81
1794978187 81
1794978192 81
1794978197 81
1794978202 81
1794978207 81
1794978212 81
1794978217 81
1794978222 81
1794978227 81
1794978232 81
```
</details>

---

