---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 11:48:07 EDT

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 83-93 cores)</summary>

```
1786462923 93
1786462928 93
1786462933 93
1786462938 93
1786462943 85
1786462948 85
1786462953 85
1786462958 85
1786462963 85
1786462968 85
1786462973 85
1786462978 85
1786462983 85
1786462988 85
1786462993 85
1786462998 85
1786463003 85
1786463008 85
1786463013 85
1786463018 85
```
</details>

---

