---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-16 12:13:00 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 9 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 11 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (5 unique values: 30-37 cores)</summary>

```
1789574827 37
1789574832 37
1789574837 37
1789574842 32
1789574847 32
1789574852 32
1789574857 32
1789574862 32
1789574867 32
1789574872 33
1789574877 33
1789574882 35
1789574887 35
1789574892 30
1789574897 30
1789574902 30
1789574907 30
1789574912 30
1789574917 30
1789574922 30
```
</details>

---

