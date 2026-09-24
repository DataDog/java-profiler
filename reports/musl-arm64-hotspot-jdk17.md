---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 06:19:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 9 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1790244843 47
1790244848 47
1790244853 47
1790244858 47
1790244863 48
1790244868 48
1790244873 48
1790244878 46
1790244883 46
1790244888 46
1790244893 46
1790244898 46
1790244903 46
1790244908 46
1790244913 46
1790244918 46
1790244923 46
1790244928 48
1790244933 48
1790244938 47
```
</details>

---

