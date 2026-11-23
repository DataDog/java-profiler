---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 00:00:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 13 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1795409848 54
1795409853 54
1795409858 54
1795409863 54
1795409868 54
1795409873 54
1795409878 54
1795409883 54
1795409888 54
1795409893 54
1795409898 54
1795409903 59
1795409908 59
1795409913 59
1795409918 59
1795409923 59
1795409928 59
1795409933 59
1795409938 59
1795409943 59
```
</details>

---

