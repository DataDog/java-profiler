---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-18 21:23:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 13-16 cores)</summary>

```
1792372752 16
1792372757 16
1792372762 16
1792372767 16
1792372772 16
1792372777 16
1792372782 16
1792372787 16
1792372792 16
1792372797 16
1792372802 16
1792372807 16
1792372812 16
1792372817 16
1792372822 16
1792372827 16
1792372832 16
1792372837 16
1792372842 16
1792372847 16
```
</details>

---

