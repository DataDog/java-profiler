---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 08:20:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 153 |
| Sample Rate | 2.55/sec |
| Health Score | 159% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1791548034 42
1791548039 42
1791548044 47
1791548049 47
1791548054 47
1791548059 47
1791548064 47
1791548069 47
1791548074 47
1791548079 47
1791548084 47
1791548089 47
1791548094 47
1791548099 47
1791548104 47
1791548109 47
1791548114 47
1791548119 47
1791548124 47
1791548129 47
```
</details>

---

