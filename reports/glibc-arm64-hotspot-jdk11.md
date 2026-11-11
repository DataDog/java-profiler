---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 15:16:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794427968 48
1794427973 48
1794427978 48
1794427983 48
1794427988 48
1794427993 48
1794427998 48
1794428003 48
1794428008 48
1794428013 48
1794428018 48
1794428023 48
1794428028 48
1794428033 48
1794428038 48
1794428043 48
1794428048 48
1794428053 48
1794428058 48
1794428063 48
```
</details>

---

