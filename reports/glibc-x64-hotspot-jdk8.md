---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-02 11:55:33 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 64-82 cores)</summary>

```
1788364245 64
1788364250 64
1788364255 64
1788364260 64
1788364265 64
1788364270 64
1788364275 64
1788364280 64
1788364285 64
1788364290 64
1788364295 64
1788364300 64
1788364305 64
1788364310 64
1788364315 64
1788364320 64
1788364325 76
1788364330 76
1788364335 76
1788364340 74
```
</details>

---

