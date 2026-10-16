---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 01:04:58 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 8 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 38-58 cores)</summary>

```
1792126801 58
1792126806 58
1792126811 58
1792126816 58
1792126821 58
1792126826 58
1792126831 58
1792126836 58
1792126841 58
1792126846 58
1792126851 38
1792126856 38
1792126861 38
1792126866 38
1792126871 38
1792126876 38
1792126881 38
1792126886 38
1792126891 38
1792126896 38
```
</details>

---

