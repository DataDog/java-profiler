---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-15 10:59:07 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 11 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 15-23 cores)</summary>

```
1792075928 15
1792075933 15
1792075938 15
1792075943 15
1792075948 15
1792075953 15
1792075958 15
1792075963 15
1792075968 15
1792075973 15
1792075978 15
1792075983 15
1792075988 15
1792075993 15
1792075998 15
1792076003 15
1792076008 18
1792076013 18
1792076018 18
1792076023 18
```
</details>

---

