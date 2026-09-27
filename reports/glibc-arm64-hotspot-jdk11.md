---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-27 00:58:56 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 14-34 cores)</summary>

```
1790484802 29
1790484807 29
1790484812 29
1790484817 29
1790484822 29
1790484827 29
1790484832 29
1790484837 29
1790484842 29
1790484847 29
1790484852 34
1790484857 34
1790484862 34
1790484867 34
1790484872 34
1790484877 34
1790484882 34
1790484887 34
1790484892 34
1790484897 34
```
</details>

---

