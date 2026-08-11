---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 11:48:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 307 |
| Sample Rate | 5.12/sec |
| Health Score | 320% |
| Threads | 11 |
| Allocations | 132 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1786462933 32
1786462938 32
1786462943 32
1786462948 32
1786462953 32
1786462958 32
1786462963 32
1786462968 32
1786462973 32
1786462978 32
1786462983 32
1786462988 32
1786462993 32
1786462998 32
1786463003 32
1786463008 27
1786463013 27
1786463018 27
1786463023 27
1786463028 27
```
</details>

---

