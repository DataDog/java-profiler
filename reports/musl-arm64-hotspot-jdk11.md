---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:48:04 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 9 |
| Allocations | 212 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 980 |
| Sample Rate | 16.33/sec |
| Health Score | 1021% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789731848 48
1789731853 48
1789731858 48
1789731863 48
1789731868 48
1789731873 48
1789731878 48
1789731883 48
1789731888 48
1789731893 48
1789731898 48
1789731903 48
1789731908 48
1789731913 48
1789731918 48
1789731923 48
1789731928 43
1789731933 43
1789731938 43
1789731943 43
```
</details>

---

