---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 09:48:43 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 925 |
| Sample Rate | 15.42/sec |
| Health Score | 964% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 26-46 cores)</summary>

```
1790171054 36
1790171059 36
1790171064 36
1790171069 36
1790171074 36
1790171079 36
1790171084 36
1790171089 36
1790171094 36
1790171099 26
1790171104 26
1790171109 26
1790171114 26
1790171119 26
1790171124 26
1790171129 46
1790171134 46
1790171139 46
1790171144 46
1790171149 46
```
</details>

---

